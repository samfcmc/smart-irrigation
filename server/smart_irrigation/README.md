Smart Irrigation Web Application
=====================
Web application developed using Django framework.
In this application, there are users and each user can create configurations for plants or get 
configurations from other users.

# Requirements
* Python >=3.0
* <a href="https://virtualenv.readthedocs.org/en/latest/">Virtualenv</a>
* <a href="http://nodejs.org/">NodeJS</a>
* <a href="http://bower.io/">Bower</a>

# Run
* Create a virtual environment:
```
virtualenv env
```
* Activate it:
```
source env/bin/activate
```
* Install the dependencies
```
pip install -r requirements.txt
```
* By default, this project uses a SQLite database
* Create the database and apply the migrations to it:
```
python manage.py migrate
```
* Create the super user:
```
python manage.py createsuperuser
```
* You will be asked to provide an username, password and e-mail. Type them as you are asked to.
* Install the client-side dependencies (such as Boostrap, AngularJS, etc)
```
python manage.py bower install
```
* Run the web server
```
python manage.py runserver
```
* Open your browser and go to <a href="http://localhost:8000/app">http://localhost:8000/app</a>
