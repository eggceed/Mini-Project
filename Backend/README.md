# BACKEND
## get -> /light/
## put -> /light/
## database structure:
### class Room(BaseModel):
    id:int
    name:str = ''
    intensity:int=100
    powered:bool=False
    isAuto:bool=False
### class Req_dep(BaseModel):
    type:str = ''
