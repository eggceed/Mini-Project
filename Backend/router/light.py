from pydantic import BaseModel
from datetime import datetime,timedelta
from fastapi import APIRouter,HTTPException
from config.database import *
from typing import Union,Optional,List

class Room(BaseModel):
    id:int
    powered:Union[bool,None] = None
    isAuto:Union[bool,None] = None
    name:str = ''
    intensity:int=100

class Req_dep(BaseModel):
    type:str = ''

router = APIRouter(prefix='/light')

if(collection.count_documents({})==0):
    collection.insert_many([
        {'id':1,'name':'Living Room','intensity':100,'powered':False,'isAuto':False},
        {'id':2,'name':'Bedroom','intensity':100,'powered':False,'isAuto':False},
        {'id':3,'name':'Kitchen','intensity':100,'powered':False,'isAuto':False}
    ])

@router.get('/')
def view_roomdata():
    return list(collection.find({},{'_id':0}))

@router.put('/')
def update_roomdata(room:Room,req_dep:Req_dep):
    if(room.id < 1 or room.id > 4):
        raise HTTPException(status_code=400,detail="Room id is invalid")
    if req_dep.type=='device':
        collection.update_one({'id':room.id},{'$set':{'powered':room.powered}})
    elif(req_dep.type=='web'):
        if(room.intensity < 0 or room.intensity > 100 ):
            raise HTTPException(status_code=400,detail="Intensity is invalid")
        if(room.name == ''):
            raise HTTPException(status_code=400,detail="Room name is invalid")
        if(room.powered == None):
            raise HTTPException(status_code=400,detail='powered is empty')
        if(room.isAuto == None):
            raise HTTPException(status_code=400,detail='isAuto is empty')
        collection.update_one({'id':room.id},{'$set':{'intensity':room.intensity,'isAuto':room.isAuto,'powered':room.powered}})
    else:
        raise HTTPException(status_code=400,detail="type is invalid")
    return {"msg":"success"}

