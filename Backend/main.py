from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from typing import Union,Optional
from pydantic import BaseModel
from router import light

app = FastAPI()

origins = ["*"]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)




app = FastAPI()
app.include_router(light.router)

@app.get("/")
def root():
    return {"msg":"welcome to root page"}