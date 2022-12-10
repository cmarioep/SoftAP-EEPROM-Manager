import '../styles/components/Button.scss';

export const Button = ({ label, link }) => {

    return (
        <a className='Button' href={link} rel="noreferrer">{label}</a>
    )

}