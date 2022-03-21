<template lang="pug">
.chart
  .cpu-view.echarts-view(ref="view")
</template>

<script lang="ts">
export default {
  name: "CpuChart",
};
</script>

<script lang="ts" setup>
import { ref, onMounted, onUnmounted, defineProps } from "vue";
import { useI18n } from "vue-i18n";
import * as echarts from "echarts";

import { useMonitorStore } from "@/stores/monitor";

const { t } = useI18n();
const monitor = useMonitorStore();

const props = defineProps({
  sampleRate: {
    type: Number,
    default: 1000,
  },
  samples: {
    type: Number,
    default: 120,
  },
});

const view = ref();

onMounted(() => {
  const chart = echarts.init(view.value);
  const resizeHandler = () => chart.resize();

  const update = () => {
    chart.setOption(buildChart());
  };

  const timer = window.setInterval(update, props.sampleRate);
  window.addEventListener("resize", resizeHandler);
  onUnmounted(() => {
    window.clearInterval(timer);
    window.removeEventListener("resize", resizeHandler);
  });
});

const buildChart = () => {
  return {
    title: {
      text: t("el.perfcat.cpuStats"),
      left: "1%",
    },
    xAxis: {
      type: "time",
    },
    yAxis: {
      type: "value",
      min: 0,
      max: 100,
      axisLabel: {
        formatter: "{value} %",
      },
    },
    tooltip: {
      trigger: "axis",
    },
    visualMap: {
      top: 50,
      right: 10,
      pieces: [
        {
          gt: 0,
          lte: 50,
          color: "#3D9140",
        },
        {
          gt: 50,
          lte: 90,
          color: "#FF6100",
        },
        {
          gt: 90,
          color: "#FF0000",
        },
      ],
    },
    series: {
      name: "CPU Usage (%)",
      type: "line",
      data: monitor.rawData.cpuUsage
        .slice(-props.samples)
        .map((dat) => [dat[0], dat[1] * 100]),
    },
  };
};
</script>

<style lang="stylus">
.echarts-view
  width 100%
  min-height 250px
</style>
