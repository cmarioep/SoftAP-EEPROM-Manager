import { useState } from "react";

import { WeakSignal, FairSignal, GoodSignal, ExcelentSignal } from "./icons";

import '../styles/components/NetworkItem.scss';


export const NetworkItem = ({ ssid, rssi }) => {

    const [isActive, setIsActive] = useState(false);

    const onClickHandler = () => {
        setIsActive(!isActive)
    }

    const signal = rssi;

    const matchIcon = () => {

        const signalValue = Math.abs(signal);

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

        <form className="networkItem" action="saveConfig" method='get'>

            <div className="networkItem__info" onClick={onClickHandler}>

                <div className="networkItem__info__icon">
                    {matchIcon()}
                </div>

                <label className="networkItem__info__ssid" htmlFor="ssid">
                    <input type="text"
                        name="ssid"
                        value={ssid}
                        readOnly
                    />
                    Tap to config
                </label>

            </div>


            {
                (isActive && <div className="networkItem__pass">

                    <label className="networkItem__pass__label" htmlFor="pass">
                        <input
                            className="networkItem__pass__input"
                            type="password"
                            name="pass"
                            placeholder="Password"
                        />
                    </label>

                    <input
                        className="networkItem__pass__button"
                        type='submit'
                        value='Save'
                    />

                </div>)
            }



        </form>
    )

}