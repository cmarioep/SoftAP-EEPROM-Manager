import { Button } from "../components/Button";

export const Home = () => {


    return (
        <div className="app-container abs-100vh ">

            <header className="app-container-title">
                <h1>ESP Wifi-Mannager</h1>
            </header>

            <div className="app-container-items border-top">
                <Button label="Wifi Configuration" link="google.com" />
                <Button label="General Configuration" link="/wificonfig" />
                <Button label="Restart" link="google.com" />
            </div>

        </div>
    )

}