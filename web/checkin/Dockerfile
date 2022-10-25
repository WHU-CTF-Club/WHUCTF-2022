FROM python:3.9.9
WORKDIR /app
COPY . /app
RUN pip install -r requirements.txt
#RUN echo $FLAG > /home/$USER/flag && export FLAG=not_flag && FLAG=not_flag 
EXPOSE 80
CMD ["python","app.py"]

