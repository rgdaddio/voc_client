#!/usr/bin/python
import json
import urllib2

server = "23.79.234.237"
provider = "hlstest3"
access_token = "hlstest3"


header =  {
    'Content-Type': 'application/json'
}


data = {
    "content_provider_id": provider,
    "access_token": access_token, 
    "thumb_length": 11768,
    "content_length": 2299653,
    "content_tags": [ ], 
    "thumb_height": "80", 
    "content_description": "For Bigger Escapes!", 
    "content_unique_id": "bbb-mp4", 
    "content_title": "For Bigger Escapes", 
    "thumb_width": "80", 
    "content_expiration": None, 
    "long_lived": True, 
    "sdk_metadata_passthrough": None, 
    "ad_url": None, 
    "content_bit_rate": 1,
    "streams": [
        {
            "url": "https://raw.githubusercontent.com/rgdaddio/voc_client/master/test/ForBiggerEscapes.mp4", 
            "type": "mp4", 
            "size": "2299653",
            "quality": '5'
        },
        {
            "url": "https://raw.githubusercontent.com/rgdaddio/voc_client/master/test/ForBiggerEscapes.mp4", 
            "type": "mp4", 
            "size": "22718509",
            "quality": '10'
        },       
    ], 
    "content_duration": 300, 
    "persistToExpiration": None, 
    "content_categories": [
        "Business"
    ], 
    "publication_timestamp": "2016-09-14 12:23:23", 
    "content_video_height": "720", 
    "thumb_url": "http://s.wsj.net/public/resources/images/OB-LC946_akamai_D_20101201120055.jpg", 
    "content_video_width": "1024", 
}
 
 
 
url = 'https://{}/ingest/v1/addContent'.format(server)

req = urllib2.Request(url, headers=header, data=json.dumps(data))
try:
    con = urllib2.urlopen(req)
    print con.read()
except urllib2.HTTPError as e:
    print e
    print e.read()

