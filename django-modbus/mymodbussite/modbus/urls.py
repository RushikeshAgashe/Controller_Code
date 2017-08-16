from django.conf.urls import url
from . import views

urlpatterns = [
    url(r'^$', views.index, name='index'),
    url(r'^table.html/$', views.table, name='table'),
    url(r'^table.js/$', views.tablescript, name='tablescript'),
    url(r'^dataloader.js/$', views.tablescript, name='dataloaderscript'),
    url(r'^test.py/$', views.test, name='test'),
    url(r'^writer.py/$', views.writer, name='writer'), 
    url(r'^MPPT_Enable.py/$', views.MPPT_Enable, name='MPPT_Enable'),
    url(r'^MPPT_Disable.py/$', views.MPPT_Disable, name='MPPT_Disable'),
    url(r'^SoC_Balancing_Enable.py/$', views.SoC_Balancing_Enable, name='SoC_Balancing_Enable'),
    url(r'^SoC_Balancing_Disable.py/$', views.SoC_Balancing_Disable, name='SoC_Balancing_Disable'),
    url(r'^database.py/$', views.database, name='database'),
    url(r'^linechart.js/$', views.linechartscript, name='linechartscript'),
    url(r'^chart.html/$', views.chart, name='chart'),
    url(r'^base.html/$', views.base, name='chart'),
 ]