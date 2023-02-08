import React from 'react'
import '../styles/Card.css'


const Card = ({id, name, intensity, powered, isAuto}) => {
  return (
    <div className='card'>
        <div className='header'>
            {/* <h1>Room {id}</h1> */}
            <h1>{name}</h1>
        </div>
    </div>
  )
}

export default Card