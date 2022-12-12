import { Route, Routes } from "react-router-dom";
import { Home, WifiConfig, NodeConfig, Restart } from '../pages/';



export const AppRouter = () => {

    return (

        <Routes>
            <Route path="/" element={<Home />} />
            <Route path="/wificonfig" element={<WifiConfig />} />
            <Route path="/nodeconfig" element={<NodeConfig />} />
            <Route path="/restart" element={<Restart />} />
        </Routes>

    )

}