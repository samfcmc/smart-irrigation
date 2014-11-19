# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('app', '0004_configuration_humidity_max'),
    ]

    operations = [
        migrations.AddField(
            model_name='plant',
            name='synced',
            field=models.BooleanField(default=False),
            preserve_default=True,
        ),
    ]
