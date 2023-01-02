import { useState, useEffect } from 'react';



export const useFetchData= (url) => {

    const [data, setData] = useState(null);


    const fetchData = async () => {
        const response = await fetch(url);
        const json = await response.json();
        setData(json);
    }


    useEffect(() => {
        fetchData();
    }, [url]);


    return {
        data
    }
    
}