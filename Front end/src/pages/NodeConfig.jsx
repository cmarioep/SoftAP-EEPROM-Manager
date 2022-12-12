import { NodeInfo } from "../FakeData";


export const NodeConfig = () => {


    return (
        <div className="app-container abs-100vh ">

            <header className="app-container-title">
                <h1>General Config</h1>
            </header>

            <div className="app-container-items border-top">
                <p>SSID:  <span>{NodeInfo.ssid}</span> </p>
                <p>IP: <span>{NodeInfo.ip}</span></p>
                <p>Mac: <span>{NodeInfo.mac}</span></p>

            </div>

        </div>
    )

}