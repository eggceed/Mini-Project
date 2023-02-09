# BACKEND
## get -> /light/
## put -> /light/
## database structure:
### class Room(BaseModel):
    id:int
    name:str = '' 
    type:str = 'web' ->web or device
    intensity:int=100
    powered:bool=False
    isAuto:bool=False
### 