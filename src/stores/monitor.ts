import { defineStore } from "pinia";

import { IBackend, IDevice, IApplication, ISurface } from "@/backends/ibackend";

export interface MonitorTarget {
  backend: IBackend | null;
  device: IDevice | null;
  application: IApplication | null;
  surface: ISurface | null;
  targetFps: number;
}
interface MonitorStore {
  target: MonitorTarget;
  rawData: {
    cpuUsage: [number, number][];
    memUsage: [number, number][];
    frameSubmits: number[];
  };
  sampler: {
    sampleRate: number;
    updateTimer: NodeJS.Timer | null;
  };
}

export const useMonitorStore = defineStore("monitor", {
  state: () => {
    return {
      target: {
        backend: null,
        device: null,
        application: null,
        surface: null,
        targetFps: 60,
      },
      rawData: {
        cpuUsage: [],
        memUsage: [],
        frameSubmits: [],
      },
      sampler: {
        sampleRate: 1000,
        updateTimer: null,
      },
    } as MonitorStore;
  },
  actions: {
    submit(target: MonitorTarget) {
      this.target.backend = target.backend;
      this.target.device = target.device;
      this.target.application = target.application;
      this.target.surface = target.surface;
      this.target.targetFps = target.targetFps;
      this.clearData();
      this.resetSampler();
    },
    clearData() {
      this.rawData.cpuUsage = [];
      this.rawData.memUsage = [];
      this.rawData.frameSubmits = [];
    },
    resetSampler() {
      if (this.sampler.updateTimer != null) {
        clearInterval(this.sampler.updateTimer);
      }
      const updateSampler = () => {
        this.addCpuUsageSample();
        this.addMemUsageSample();
      };
      this.sampler.updateTimer = setInterval(
        updateSampler,
        this.sampler.sampleRate
      );
    },
    async addCpuUsageSample() {
      if (this.target.device != null) {
        const time = Date.now();
        const data = await this.target.device.getCpuUsage();
        this.rawData.cpuUsage.push([time, data]);
      }
    },
    async addMemUsageSample() {
      if (this.target.device != null) {
        const time = Date.now();
        const data = await this.target.device.getMemUsage();
        this.rawData.memUsage.push([time, data]);
      }
    },
  },
});
