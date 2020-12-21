<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.4" tiledversion="2020.11.25" name="fly_going" tilewidth="32" tileheight="32" tilecount="7" columns="7">
 <image source="../Content/panstarrs/fly_going.png" width="224" height="32"/>
 <tile id="0">
  <properties>
   <property name="originX" type="int" value="16"/>
   <property name="originY" type="int" value="16"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="2" name="Collision" type="Collision" x="10" y="10" width="13" height="18.875"/>
  </objectgroup>
  <animation>
   <frame tileid="0" duration="100"/>
   <frame tileid="1" duration="100"/>
   <frame tileid="2" duration="100"/>
   <frame tileid="3" duration="100"/>
   <frame tileid="4" duration="100"/>
   <frame tileid="5" duration="100"/>
   <frame tileid="6" duration="100"/>
  </animation>
 </tile>
</tileset>
