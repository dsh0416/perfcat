import { defineStore } from "pinia";

export interface Alertable {
  id: number;
  title: string;
  type: "info" | "success" | "warning" | "error";
}

interface AlertStore {
  alerts: Alertable[];
}

export const useAlertStore = defineStore("alert", {
  state: () => {
    return { alerts: [] } as AlertStore;
  },
  actions: {
    alert(title: string, type: "info" | "success" | "warning" | "error") {
      this.alerts.push({ id: this.alerts.length, title, type });
    },
  },
});
