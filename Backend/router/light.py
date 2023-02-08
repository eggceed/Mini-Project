from pydantic import BaseModel
from datetime import datetime,timedelta
from fastapi import APIRouter,HTTPException
from config.database import *
from typing import Union,Optional,List

class Room(BaseModel):
    id:int
    name:str = '' 
    type:str 
    intensity:int=100
    powered:bool=False
    isAuto:bool=False

router = APIRouter(prefix='/light')

@router.get('/')
def view_roomdata():
    return list(collection.find())

@router.put('/')
def update_roomdata(room:Room):
    if(room.id < 1 or room.id > 4):
        raise HTTPException(status_code=400,detail="Room id is invalid")
    if room.type=='device':
        collection.update_one({'id':room.id},{'$set':{'powered':room.powered}})
    elif(room.type=='web'):
        if(room.intensity < 0 or room.intensity > 100):
            raise HTTPException(status_code=400,detail="Intensity is invalid")
        if(room.name == ''):
            raise HTTPException(status_code=400,detail="Room name is invalid")
        collection.update_one({'id':room.id},{'$set':{'intensity':room.intensity,'isAuto':room.isAuto,'powered':room.powered}})
    return {"msg":"success"}

