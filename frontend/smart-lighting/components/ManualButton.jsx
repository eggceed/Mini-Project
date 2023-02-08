import React, { Fragment } from 'react'
import Switch from 'react-input-switch';
import { useState } from 'react'
import '../styles/Button.css'


const ManualButton = () => {
    const [value, setValue] = useState('off');
    const disabled = false;
    return (
        <div className='component'>
        <Fragment>
        {value}
        <Switch
            value={value}
            on="on"
            off="off"
            onChange={setValue}
            disabled={disabled}
        />
        </Fragment>
        </div>
        
    );
}

export default ManualButton;
