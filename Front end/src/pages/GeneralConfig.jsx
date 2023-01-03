import { useFetchData } from '../hooks/useFetchData';


import { TapBar } from "../components/TapBar";
// import { NodeInfo } from "../FakeData";

const nodeInfo = 'http://192.168.4.1/nodeinfo';



export const GeneralConfig = () => {

    const { data } = useFetchData(nodeInfo);


    if (!data) {

        return (

            <div className="app-container abs-100vh">

                <header className="app-container-title">
                    <h1>General Config</h1>
                </header>


                <p className="app-container-items">Loading...</p>

            </div>)

    }


    return (
        <div className="app-container abs-100vh ">

            <header className="app-container-title">
                <h1>General Config</h1>
            </header>

            <div className="app-container-items">
                <div className="app-container-items-generalinfo">
                    <p><span className="app-container-items-generalinfo-label">SSID:</span>
                        <span className="app-container-items-generalinfo-info">{data.ssid}</span> </p>

                    <p><span className="app-container-items-generalinfo-label">IP:</span>
                        <span className="app-container-items-generalinfo-info">{data.ip}</span></p>

                    <p><span className="app-container-items-generalinfo-label">MAC:</span>
                        <span className="app-container-items-generalinfo-info">{data.mac}</span></p>
                </div>
            </div>

            <TapBar />

        </div>
    )

}