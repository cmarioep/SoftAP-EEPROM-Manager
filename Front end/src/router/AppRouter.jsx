import { Route, Routes } from "react-router-dom";
import { Home, WifiConfig } from '../pages/';


export const AppRouter = () => {

    return (

        <Routes>
            <Route path="/" element={<Home />} />
            <Route path="/wificonfig" element={<WifiConfig />} />
        </Routes>

    )

}