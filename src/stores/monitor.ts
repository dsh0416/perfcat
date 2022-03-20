import { defineStore } from "pinia";

import { IBackend, IDevice, IApplication, ISurface } from "@/backends/ibackend";

interface MonitorStore {
  backend: IBackend | null;
  device: IDevice | null;
  application: IApplication | null;
  surface: ISurface | null;
  targetFps: number;
}

export const useMonitorStore = defineStore("monitor", {
  state: () => {
    return {
      backend: null,
      device: null,
      application: null,
      surface: null,
      targetFps: 60,
    } as MonitorStore;
  },
  actions: {
    submit(form: MonitorStore) {
      this.backend = form.backend;
      this.device = form.device;
      this.application = form.application;
      this.surface = form.surface;
      this.targetFps = form.targetFps;
    },
  },
});
