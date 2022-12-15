import { HomeIcon } from "../components/icons";

import '../styles/components/_TapBar.scss';

export const TapBar = () => {

    return (
        <nav className="tapBar" >
            <div className="tapBar-icon">
                <HomeIcon className="tapBar-icon"/>
                <p>Home</p>
            </div>
        </nav>
    )

}