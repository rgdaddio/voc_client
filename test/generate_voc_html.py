#!/usr/bin/python
import sys
import json

import sqlite3
import json
import cgi

conn = sqlite3.connect('voc_client.db')

class html_generator:
	conn = None
	
	def __init__(self):
		self.conn = sqlite3.connect('voc_client.db')
		self.conn.row_factory = self.dict_factory
		

	def dict_factory(self, cursor, row):
		d = {}
		for idx, col in enumerate(cursor.description):
			d[col[0]] = row[idx]
		return d

	def get_categories(self):
		c = self.conn.cursor()
		
		c.execute('''select distinct category from cache_manifest order by category asc''')
		
		return([x['category'] for x in c.fetchall()])

	def get_category_contents(self, category):
		c = self.conn.cursor()
		
		c.execute('select * from cache_manifest where category = ?', (category,))
		
		return(c.fetchall())

	def build_category_header(self):
		html = ''
		for category in self.get_categories():
			html = html+'<li><a href="#'+category.replace(' ','').replace('&', '')+'">'+cgi.escape(category)+'</a></li>'
		return html

	def build_content_view(self):

		html = '<div id="about" class="page"><div class="container">'
		for category in self.get_categories():
			#print >> sys.stderr, category
			html = html+'<div id="'+category.replace(' ','').replace('&', '')+'" class="row"><h2 class="title">'+cgi.escape(category)+'</h2>'
			for item in self.get_category_contents(category):
				title=item['title']
				if len(title) <= 30: 
					pass
				else: 
					title =  title[:27] + '...' 
				html = (html+'<div class="span4 profile"><div class="image-wrap"><a href="cache/'+item['local_file']+'">'+
				'<img src="cache/'+item['local_thumbnail']+'" alt="thumbnail"></a></div>')
				html = html+'<h3 class="profile-name">'+cgi.escape(title)+'</h3></div>'
			html = html+'</div>'

		html = html+'</div></div>'
		return(html)

	def build_the_page(self):
		with open('test/voc.html', 'w') as html_file:
			html = self.build_content_view()
			header = self.build_category_header()

			html_file.write(open('test/beginning.html', 'r').read()+
										header.encode('utf-8')+
										open('test/header.html', 'r').read()+
										html.encode('utf-8')+open('test/end.html', 'r').read())

	
if __name__ == "__main__":
	gen = html_generator()
	gen.build_the_page()
	
