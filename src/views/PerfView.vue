<template lang="pug">
.perf
  cpu-chart
  mem-chart
</template>

<script lang="ts">
import CpuChart from "@/components/charts/CpuChart.vue";
import MemChart from "@/components/charts/MemChart.vue";

export default {
  name: "PerfView",
  components: { CpuChart, MemChart },
};
</script>
