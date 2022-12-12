import { Link } from "react-router-dom";

import '../styles/components/Button.scss';

export const Button = ({ label, link }) => {

    return (
        <Link className='Button' to={link} rel="noreferrer">{label}</Link>
    )

}