import pyrebase
import json
import dload
import urllib.request
import requests
from urllib.request import urlopen
from bs4 import BeautifulSoup



with open("auth.json") as f:
    config = json.load(f)

firebase=pyrebase.initialize_app(config)
db=firebase.database()


response=urlopen("https://search.naver.com/search.naver?where=nexearch&sm=top_hty&fbm=0&ie=utf8&query=%EB%B0%A9%EC%82%AC%EB%8A%A5")
soup=BeautifulSoup(response, "html.parser")

title=soup.find("div",{"class": "map"})
title2=title.text.split()
print(title2)
print()
for i in range(0,len(title2),5):
    nt=title2[i:i+5]
    db.child("epdlxj").child(nt[1]).set(nt[4])
    db.child("지역").child(nt[1]).set(nt[4])
