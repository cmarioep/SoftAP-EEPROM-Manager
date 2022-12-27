import { WeakSignal, FairSignal, GoodSignal, ExcelentSignal } from "../components/icons";


export const useSetSignalIcon = () => {

    const setIcon = (rssi) => {

        const signalValue = Math.abs(rssi);

        if (signalValue > 70) {
            return <WeakSignal />
        }

        if (signalValue > 65 && signalValue <= 70) {
            return <FairSignal />
        }

        if (signalValue > 50 && signalValue <= 65) {
            return <GoodSignal />
        }

        if (signalValue <= 50) {
            return <ExcelentSignal />
        }

    }


    return (
        {
            setIcon
        }
    )

}