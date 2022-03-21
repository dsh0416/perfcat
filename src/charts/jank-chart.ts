export const generateJankChart = (
  janks: [number[], number[]],
  bigJanks: [number[], number[]]
) => {
  return {
    title: {
      text: "Jank Statistics",
      left: "1%",
    },
    xAxis: {
      type: "time",
    },
    yAxis: {
      type: "value",
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
          lte: 1,
          color: "#3D9140",
        },
        {
          gt: 1,
          lte: 5,
          color: "#FF6100",
        },
        {
          gt: 5,
          color: "#FF0000",
        },
      ],
    },
    series: [
      {
        name: "Jank",
        type: "line",
        data: janks,
      },
      {
        name: "Big Jank",
        type: "line",
        data: bigJanks,
      },
    ],
  };
};
