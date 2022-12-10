import { NetworkItem } from "../components/NetworkItem";
import { listOfNetworks } from "../FakeData";


export const WifiConfig = () => {


    return (
        <div className="app-container min-100vh ">

            <header className="app-container-title">
                <h1>Available Networks</h1>
            </header>

            <ul className="app-container-items border-top">
                {
                    listOfNetworks.map(Network =>
                        <NetworkItem
                            key={Math.random() * 25}
                            ssid={Network.ssid}
                            rssi={Network.rssi}
                        />)
                }
            </ul>


        </div>
    )

}