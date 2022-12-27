import { useState } from "react";


const setWifiConfig = async (wifiConfig) => {

    try {

        const response = await fetch('http://localhost:3500/setwificonfig', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(wifiConfig),

        });

        // Actualiza el estado local con la respuesta de la solicitud fetch
        const status = response.status;

        if (status === 201) {
            console.log('OK')
        }


    } catch (error) {
        alert('Ocurrio un problema con la conexión al servidor!!!');
        console.error(error);
    }

}


export const useHandleForm = (initialForm = {}) => {

    const [inputText, setInputText] = useState(initialForm);
    

    const onInputChange = ({ target }) => {

        const { name, value } = target;

        setInputText(
            {
                ...inputText,
                [name]: value
            }
        );

    }


    const handleSubmit = (event) => {

        event.preventDefault();

        setWifiConfig(inputText);

    }
    

    return (
        {
            inputText,
            onInputChange,
            handleSubmit
        }
    )

}