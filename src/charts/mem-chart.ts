export const generateMemChart = (mems: [number[], number[]]) => {
  return {
    title: {
      text: "Memory Statistics",
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
      name: "Memory Usage (%)",
      type: "line",
      data: mems.map((dat) => [dat[0], dat[1] * 100]),
    },
  };
};
