import { Route, Routes } from "react-router-dom";
import { Home, WifiConfig, GeneralConfig, Restart } from '../pages/';



export const AppRouter = () => {

    return (

        <Routes>
            <Route path="/" element={<Home />} />
            <Route path="/wificonfig" element={<WifiConfig />} />
            <Route path="/nodeconfig" element={<GeneralConfig />} />
            <Route path="/restart" element={<Restart />} />
        </Routes>

    )

}