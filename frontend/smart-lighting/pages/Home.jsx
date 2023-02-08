import React, { useEffect, useState } from 'react'
import Card from '../components/Card'
import '../styles/Home.css'

const sampleData = [
    {
      "id": 1,
      "name": "Bedroom",
      "intensity": 100,
      "pewered": true,
      "isAuto": true
    },
    {
        "id": 2,
        "name": "Bedroom2",
        "intensity": 50,
        "pewered": true,
        "isAuto": true
      },
      {
        "id": 3,
        "name": "Bedroom3",
        "intensity": 20,
        "pewered": true,
        "isAuto": true
      },
]

const Home = () => {
    const [room, setRooms] = useState(sampleData)

    // useEffect(() => {

    // })

  return (
    <div>
        <h1>Smart Home Lighting</h1>
        <div className='list-room'>
        {room.map(r => <Card {...r} />)}
    </div>
    </div>
    
  )
}

export default Home