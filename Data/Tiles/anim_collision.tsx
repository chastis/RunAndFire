<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.4" tiledversion="2020.11.25" name="anim_collision" tilewidth="64" tileheight="64" tilecount="1" columns="1">
 <properties>
  <property name="originX" type="int" value="20"/>
  <property name="originY" type="int" value="36"/>
 </properties>
 <image source="../Content/panstarrs/anim_lond_standing.png" trans="ffffff" width="64" height="64"/>
 <tile id="0" type="Collision">
  <properties>
   <property name="originX" type="int" value="20"/>
   <property name="originY" type="int" value="36"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="Collision" type="Collision" x="11.4545" y="25.2727" width="14.3409" height="22"/>
   <object id="2" name="Overlap" type="Overlap" x="12.7273" y="47.2727" width="12" height="1.27273"/>
  </objectgroup>
 </tile>
</tileset>
