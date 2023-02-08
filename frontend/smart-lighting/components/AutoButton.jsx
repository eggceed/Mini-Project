import React, { Fragment } from 'react'
import Switch from 'react-input-switch';
import { useState } from 'react'
import '../styles/Button.css'

function disable(s) {
    s = false;
}

const AutoButton = () => {
    const [value, setValue] = useState('Manual');
    return (
        <div className="component">
            <Fragment>
        {value}
        <Switch
            value={value}
            on="Auto"
            off="Manual"
            onChange={setValue}
        />
        </Fragment> 
        </div>
       
    );
}

export default AutoButton;
