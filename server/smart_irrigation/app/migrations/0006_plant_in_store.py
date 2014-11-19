# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('app', '0005_plant_synced'),
    ]

    operations = [
        migrations.AddField(
            model_name='plant',
            name='in_store',
            field=models.BooleanField(default=False),
            preserve_default=True,
        ),
    ]
