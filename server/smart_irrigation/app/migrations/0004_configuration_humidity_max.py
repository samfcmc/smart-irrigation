# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('app', '0003_auto_20141117_1632'),
    ]

    operations = [
        migrations.AddField(
            model_name='configuration',
            name='humidity_max',
            field=models.IntegerField(default=0),
            preserve_default=False,
        ),
    ]
