export interface IBackend {
  name: string;
  value: string;
  available: boolean;
  getDevices(): Promise<IDevice[]>;
}

export declare interface IDevice {
  name: string;
  value: string;
  getApplications(): Promise<IApplication[]>;
  getCpuUsage(): Promise<number>; // range [0, 1]
  getMemUsage(): Promise<number>; // range [0, 1]
  getCpuCount(): number;
  getMemTotal(): number; // in bytes
}

export declare interface IApplication {
  name: string;
  value: string;
  url: string;
  pid: number;
  getSurfaces(): Promise<ISurface[]>;
}

export declare interface ISurface {
  name: string;
  value: string;
}
