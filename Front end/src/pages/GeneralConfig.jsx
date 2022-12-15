import { TapBar } from "../components/TapBar";
import { NodeInfo } from "../FakeData";


export const GeneralConfig = () => {


    return (
        <div className="app-container abs-100vh ">

            <header className="app-container-title">
                <h1>General Config</h1>
            </header>

            <div className="app-container-items">
                <div className="app-container-items-generalinfo">
                    <p><span className="app-container-items-generalinfo-label">SSID:</span>
                        <span className="app-container-items-generalinfo-info">{NodeInfo.ssid}</span> </p>

                    <p><span className="app-container-items-generalinfo-label">IP:</span>
                        <span className="app-container-items-generalinfo-info">{NodeInfo.ip}</span></p>

                    <p><span className="app-container-items-generalinfo-label">MAC:</span>
                        <span className="app-container-items-generalinfo-info">{NodeInfo.mac}</span></p>
                </div>
            </div>

            <TapBar />

        </div>
    )

}