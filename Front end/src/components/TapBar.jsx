import { Link } from "react-router-dom";
import { HomeIcon } from "../components/icons";

import '../styles/components/_TapBar.scss';

export const TapBar = () => {

    return (
        <nav className="tapBar" >
            <Link className="tapBar-icon" to="/">
                <HomeIcon className="tapBar-icon"/>
                <p>Home</p>
            </Link>
        </nav>

    )

}