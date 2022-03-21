import type { IApplication, IBackend, IDevice, ISurface } from "./ibackend";

import * as os from "os-utils";
import * as frida from "frida";

export class MacOsBackend implements IBackend {
  public name = "macOS";
  public value = "macos";
  public available = process.platform == "darwin";

  public async getDevices(): Promise<IDevice[]> {
    return [new MacOsDevice()];
  }
}

export class MacOsDevice implements IDevice {
  public name = "Local";
  public value = "local";

  public getCpuUsage(): Promise<number> {
    return new Promise<number>((resolve) => {
      os.cpuUsage((v) => {
        resolve(v);
      });
    });
  }

  public async getMemUsage(): Promise<number> {
    return 1 - os.freememPercentage();
  }

  public getCpuCount(): number {
    return os.cpuCount();
  }

  public getMemTotal(): number {
    return os.totalmem();
  }

  public async getApplications(): Promise<IApplication[]> {
    const device = await frida.getLocalDevice();
    const processes = await device.enumerateProcesses();
    return processes.map((process) => {
      return new MacOsApplication(process.name, process.pid);
    });
  }
}

export class MacOsApplication implements IApplication {
  public name = "";
  public value = "";
  public url = "";
  public pid = 0;

  constructor(name: string, pid: number) {
    this.name = `${name} (PID: ${pid})`;
    this.value = pid.toString();
    this.pid = pid;
  }

  public async getSurfaces(): Promise<ISurface[]> {
    const surfaces: ISurface[] = [];
    try {
      const session = await frida.attach(this.pid);
      await session.detach();
    } catch (e) {
      console.log(e);
    }
    return surfaces;
  }
}
