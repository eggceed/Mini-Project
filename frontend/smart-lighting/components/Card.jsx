import React, { useState } from 'react'
import '../styles/Card.css'
import Light from '../components/Light'
import ManualButton from './ManualButton'
import AutoButton from './AutoButton'

const Card = ({id, name, intensity, powered, isAuto}) => {
    
    // const [card, setCard] = useState([])
    // console.log(card)  
  return (
    <div className='card'>
        <div className='header'>
            {/* <h1>Room {id}</h1> */}
            <h1>{name}</h1> 
            {/* <p>{intensity}</p>        */}
        </div>
        
        <div className='btnlist'>
          <ManualButton/>
        <AutoButton/>
           
        </div> 
        <Light/>
    </div>
  )
}

export default Card