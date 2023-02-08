import React, { useState } from 'react'
import '../styles/Card.css'
import Light from '../components/Light'


const Card = ({id, name, intensity, powered, isAuto}) => {
    
    // const [card, setCard] = useState([])
    // console.log(card)  
  return (
    <div className='card'>
        <div className='header'>
            {/* <h1>Room {id}</h1> */}
            <h1>{name}</h1> 
            <p>{intensity}</p>       
        </div>
        <div>
            <Light/>
        </div>
    </div>
  )
}

export default Card