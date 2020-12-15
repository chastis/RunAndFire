<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.4" tiledversion="2020.11.25" name="chests" tilewidth="32" tileheight="32" tilecount="96" columns="12">
 <image source="../Content/Chests/chests.png" trans="ffffff" width="384" height="256"/>
 <tile id="58" type="Collision">
  <objectgroup draworder="index" id="2">
   <object id="2" name="Collision" type="Collision" x="6.45455" y="0" width="18.8182" height="13.1818"/>
  </objectgroup>
 </tile>
 <tile id="70">
  <animation>
   <frame tileid="58" duration="200"/>
   <frame tileid="70" duration="200"/>
   <frame tileid="82" duration="200"/>
   <frame tileid="94" duration="200"/>
  </animation>
 </tile>
</tileset>
