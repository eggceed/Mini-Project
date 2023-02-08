import React, { useState } from 'react'
import '../styles/Light.css'

const Light = ({intensity}) => {
    const [number, setNumber] = useState(intensity)

  return (
    <div className='light'>
        <button className='btn' onClick={() => setNumber(number-1)}>-</button>
        <p>{number}</p>
        <button className='btn' onClick={() => setNumber(number+1)}>+</button>
    </div>
  )
}

export default Light
