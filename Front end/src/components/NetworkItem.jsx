import { useState } from "react";


import { useHandleForm } from "../hooks/useHandleForm";


import { useSetSignalIcon } from "../hooks/useSetSignalIcon";


import '../styles/components/_NetworkItem.scss';




export const NetworkItem = ({ ssid, rssi }) => {

    const { setIcon } = useSetSignalIcon();


    const [isActive, setIsActive] = useState(false);

    const onClickHandler = () => {
        setIsActive(!isActive)
    }


    const {inputText, onInputChange, handleSubmit} = useHandleForm({ ssid, password: '' });



    return (

        <form className="networkItem" onSubmit={handleSubmit}>

            <div className="networkItem__info" onClick={onClickHandler}>

                <div className="networkItem__info__icon">
                    {setIcon(rssi)}
                </div>

                <label className="networkItem__info__ssid" htmlFor="ssid">
                    <input
                        type="text"
                        defaultValue={ssid}
                        readOnly
                    />
                    Tap to config
                </label>

            </div>


            {
                (isActive && <div className="networkItem__pass">

                    <label className="networkItem__pass__label" htmlFor="password">
                        <input
                            className="networkItem__pass__input"
                            type="password"
                            name="password"
                            placeholder="Password"
                            value={inputText.password}
                            onChange={onInputChange}
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

