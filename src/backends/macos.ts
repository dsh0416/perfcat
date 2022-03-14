// import { Application, Backend, Device } from "./backend";

// export default class MacOsBackend implements Backend {
//   public name = "macOS";
//   public value = "macos";
//   public available = process.platform == "darwin";

//   public async getDevices(): Promise<Device[]> {
//     return [new MacOsDevice()];
//   }
// }

// class MacOsDevice implements Device {
//   public name = "native";
//   public value = "native";

//   public async getApplications(): Promise<Application[]> {
//     throw new Error("Method not implemented.");
//   }
// }
