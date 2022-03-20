<template lang="pug">
.perf
  .frame-view.echarts-view(ref="frameView")
  .cpu-view.echarts-view(ref="cpuView")
  .mem-view.echarts-view(ref="memView")
</template>

<script lang="ts">
import * as echarts from "echarts";
import type {
  IBackend,
  IDevice,
  IApplication,
  ISurface,
} from "@/backends/ibackend";

export default {
  name: "PerfView",
};
</script>

<script lang="ts" setup>
import { ref, reactive, onMounted, onUnmounted } from "vue";
import { generateFrameChart } from "@/charts/frame-chart";
import { generateCpuChart } from "@/charts/cpu-chart";
import { generateMemChart } from "@/charts/mem-chart";

const frameView = ref();
const cpuView = ref();
const memView = ref();

const chartData = reactive({
  frameData: [[], []] as [number[], number[]],
  cpuData: [[], []] as [number[], number[]],
  memData: [[], []] as [number[], number[]],
});

const submitted = reactive({
  backend: null as IBackend | null,
  device: null as IDevice | null,
  application: null as IApplication | null,
  surface: null as ISurface | null,
});

const dataUpdate = async () => {
  const time = Date.now();
  if (submitted.backend == null || submitted.device == null) {
    chartData.cpuData.push([time, 0]);
    chartData.memData.push([time, 0]);
    chartData.frameData.push([time, 0]);
    return;
  }

  if (submitted.surface == null) {
    const cpu = await submitted.device.getCpuUsage();
    const mem = await submitted.device.getMemUsage();
    chartData.cpuData.push([time, cpu]);
    chartData.memData.push([time, mem]);
    chartData.frameData.push([time, 0]);
    return;
  }

  const cpu = await submitted.device.getCpuUsage();
  const mem = await submitted.device.getMemUsage();
  // TODO: Get FPS
  chartData.cpuData.push([time, cpu]);
  chartData.memData.push([time, mem]);
  chartData.frameData.push([time, 0]);
};

onMounted(() => {
  const frameChart = echarts.init(frameView.value);
  const cpuChart = echarts.init(cpuView.value);
  const memChart = echarts.init(memView.value);

  // submitted.backend = ;
  // submitted.device = new MacOsDevice();

  const chartUpdate = () => {
    dataUpdate();
    frameChart.setOption(generateFrameChart(chartData.frameData));
    cpuChart.setOption(generateCpuChart(chartData.cpuData));
    memChart.setOption(generateMemChart(chartData.memData));
  };

  const resizeHandler = () => {
    frameChart.resize();
    cpuChart.resize();
    memChart.resize();
  };

  const timer = window.setInterval(chartUpdate, 1000);
  window.addEventListener("resize", resizeHandler);
  onUnmounted(() => {
    window.clearInterval(timer);
    window.removeEventListener("resize", resizeHandler);
  });
});
</script>

<style lang="stylus">
.echarts-view
  width 100%
  min-height 250px
</style>
