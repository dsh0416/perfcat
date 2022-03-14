export const generateFrameChart = (frames: [number[], number[]]) => {
  return {
    title: {
      text: "Frame Statistics",
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
          lte: 50,
          color: "#FF0000",
        },
        {
          gt: 45,
          lte: 55,
          color: "#FF6100",
        },
        {
          gt: 55,
          color: "#3D9140",
        },
      ],
    },
    series: {
      name: "FPS",
      type: "line",
      data: frames,
    },
  };
};
