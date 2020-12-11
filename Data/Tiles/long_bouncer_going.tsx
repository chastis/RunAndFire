<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.4" tiledversion="2020.11.25" name="long_bouncer_going" tilewidth="64" tileheight="64" tilecount="6" columns="6">
 <image source="../Content/panstarrs/long_bouncer_going.png" width="384" height="64"/>
 <tile id="0">
  <properties>
   <property name="originX" type="int" value="11"/>
   <property name="originY" type="int" value="32"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="Collision" type="Collision" x="4" y="22" width="14" height="21"/>
  </objectgroup>
  <animation>
   <frame tileid="0" duration="100"/>
   <frame tileid="1" duration="100"/>
   <frame tileid="2" duration="100"/>
   <frame tileid="3" duration="100"/>
   <frame tileid="4" duration="100"/>
   <frame tileid="5" duration="100"/>
  </animation>
 </tile>
</tileset>
