import type { IApplication, IBackend, IDevice } from "./ibackend";

const { os } = window.native;

export class MacOsBackend implements IBackend {
  public name = "macOS";
  public value = "macos";
  public available = process.platform == "darwin";

  public async getDevices(): Promise<IDevice[]> {
    return [new MacOsDevice()];
  }
}

export class MacOsDevice implements IDevice {
  public name = "Native";
  public value = "native";

  public getCpuUsage(): Promise<number> {
    return new Promise<number>((resolve) => {
      os.cpuUsage((v) => {
        resolve(v);
      });
    });
  }

  public async getMemUsage(): Promise<number> {
    console.log(os.freemem());
    return 1 - os.freememPercentage();
  }

  public getCpuCount(): number {
    return os.cpuCount();
  }

  public getMemTotal(): number {
    return os.totalmem();
  }

  public async getApplications(): Promise<IApplication[]> {
    return [];
  }
}
