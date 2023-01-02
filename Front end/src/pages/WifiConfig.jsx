import { NetworkItem } from "../components/NetworkItem";
import { TapBar } from "../components/TapBar";

import { useFetchData } from '../hooks/useFetchData';


const listOfNetworks = 'http://localhost:3500/wifiscan';


export const WifiConfig = () => {

    const { data } = useFetchData(listOfNetworks);


    if (!data) {

        return (

            <div className="app-container min-100vh">

                <header className="app-container-title">
                    <h1>Available Networks</h1>
                </header>


                <p className="app-container-items">Loading...</p>

            </div>)

    }


    return (

        <div className="app-container min-100vh">

            <header className="app-container-title">
                <h1>Available Networks</h1>
            </header>


            <ul className="app-container-items">
                {
                    data.map((Network, index) =>
                        <NetworkItem
                            key={index}
                            ssid={Network.ssid}
                            rssi={Network.rssi}
                        />)
                }
            </ul>

            <TapBar />

        </div>

    )

}


