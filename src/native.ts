export {};

declare global {
  interface Window {
    native: {
      os: typeof import("os-utils");
      process: typeof process;
    };
  }
}
