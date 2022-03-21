import * as os from "os-utils";
import * as frida from "frida";

import { useAlertStore } from "@/stores/alert";

import type { IApplication, IBackend, IDevice, ISurface } from "./ibackend";

export class WindowsBackend implements IBackend {
  public name = "Windows";
  public value = "windows";
  public available = process.platform == "win32";

  public async getDevices(): Promise<IDevice[]> {
    return [new WindowsDevice()];
  }
}

export class WindowsDevice implements IDevice {
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
      return new WindowsApplication(process.name, process.pid);
    });
  }
}

export class WindowsApplication implements IApplication {
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
      useAlertStore().alert((e as Error).message, "error");
    }
    return surfaces;
  }
}
