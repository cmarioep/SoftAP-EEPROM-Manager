import { Button } from "../components/Button";

export const Home = () => {


    return (
        <div className="app-container abs-100vh ">

            <header className="app-container-title">
                <h1>Smart Switch</h1>
            </header>

            <div className="app-container-items border-top">
                <Button label="Config Smart Switch" link="google.com" />
                <Button label="Config Wifi" link="/wificonfig" />
                <Button label="Restart" link="google.com" />
            </div>

        </div>
    )

}